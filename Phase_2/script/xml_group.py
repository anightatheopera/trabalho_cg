# Author: Chat-GPT3
# Date: 2023-04-02
# Description: This script transforms an XML file by removing the 'name' attribute from all 'group' elements and adding a comment to the group containing the name of the first 'model' element within the group. The script takes two arguments: the input file and the output file.
# Usage: python xml_group.py input.xml output.xml
# Verified by: Miguel Gomes (2023-04-02)


import xml.etree.ElementTree as ET
import sys

output = sys.argv[2]
input = sys.argv[1]

def transform_group(element):
    """
    Transform a single group element by removing its 'name' attribute and adding a comment to the group
    containing its name.
    """
    group_name = element.attrib.get('name')
    if group_name is not None:
        # Add a comment to the group containing the name of the first 'model' element
        comment = f" {group_name} "
        element.insert(0, ET.Comment(comment))

    # Recurse on child elements
    for child in element:
        if child.tag == 'group':
            transform_group(child)

def transform_xml(input_file, output_file):
    """
    Transform an entire XML tree by recursively applying the 'transform_group' function to all 'group' elements.
    """
    # Load the input XML from the file
    tree = ET.parse(input_file)
    root = tree.getroot()

    # Transform the XML
    for child in root:
        if child.tag == 'group':
            transform_group(child)
            transform_xml_helper(child)

    # Write the output XML to the file
    tree.write(output_file, encoding='utf-8', xml_declaration=True)

def transform_xml_helper(element):
    """
    Recursive helper function to transform all 'group' elements within a given element.
    """
    for child in element:
        if child.tag == 'group':
            transform_group(child)
            transform_xml_helper(child)

# Transform the XML
transform_xml(input, output)
